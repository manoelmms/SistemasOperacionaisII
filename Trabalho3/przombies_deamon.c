// Implementar um daemon(*) que, de n em n segundos (argumento do programa) acorda e escreve em um arquivo 
// próprio de log informações sobre os processos ZOMBIEs do sistema.
//
// O  daemon,  que  trabalha  em  background,  finaliza  sua  execução 
// quando  recebe  um  SIGTERM,  que  deve  ser  interceptado  e  gerar  mensagens  de  finalização  no  arquivo  de 
// log. Aos demais sinais (exceto obviamente o SIGKILL), o daemon deve ser invulnerável.

#define _POSIX_C_SOURCE 200809L // Para strftime, sigaction, etc.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LOG_FILE "zombie_monitor.log"
#define MAX_LINE 256
#define DEBUG 1

volatile sig_atomic_t keep_running = 1;

// Handler para SIGTERM
void sigterm_handler(int signum) {
    keep_running = 0;
}

// Handler genérico para ignorar outros sinais
void ignore_signal(int signum) {
    printf("Sinal %d ignorado.\n", signum);
}

// Função para obter timestamp formatado
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Função para escrever no arquivo de log
void write_debug_log(FILE *log_file, const char *message) {
    if (DEBUG) {
        char timestamp[64];
        get_timestamp(timestamp, sizeof(timestamp));
        fprintf(log_file, "[%s] %s\n", timestamp, message);
        fflush(log_file);
    }
}

// Estrutura para armazenar informações de um processo zombie
typedef struct {
    pid_t pid;
    pid_t ppid;
    char comm[MAX_LINE];
} ZombieInfo;

// Função para verificar se um processo é zombie e obter suas informações
// Retorna 1 se for zombie e preenche info, retorna 0 caso contrário
int get_zombie_info(pid_t pid, ZombieInfo *info) {
    char path[MAX_LINE];
    char line[MAX_LINE];
    char comm[MAX_LINE] = "unknown";
    pid_t ppid = 0;
    char state = '?';
    FILE *fp;
    
    // Abrir arquivo stat do processo (apenas uma vez)
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    fp = fopen(path, "r");
    
    if (fp == NULL) {
        return 0;
    }
    
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Parse do formato: pid (comm) state ppid ...
        char *start = strchr(line, '(');
        char *end = strrchr(line, ')');
        
        if (start != NULL && end != NULL) {
            // Extrair nome do comando
            size_t len = end - start - 1;
            if (len < sizeof(comm)) {
                strncpy(comm, start + 1, len);
                comm[len] = '\0';
            }
            
            // Extrair estado e PPID
            char *p = end + 2;
            state = *p;
            if (sscanf(p, " %*c %d", &ppid) != 1) {
                ppid = 0;
            }
        }
    }
    
    fclose(fp);
    
    // Verificar se é zombie
    if (state == 'Z') {
        info->pid = pid;
        info->ppid = ppid;
        strncpy(info->comm, comm, MAX_LINE - 1);
        info->comm[MAX_LINE - 1] = '\0';
        return 1;
    }
    return 0;
}

// Função para escanear e logar processos zombies
void scan_zombies(FILE *log_file) {
    DIR *proc_dir;
    struct dirent *entry;
    ZombieInfo zombies[1024];
    int zombie_count = 0;

    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        write_debug_log(log_file, "ERRO: Não foi possível abrir /proc");
        return;
    }
    
    // Coletar todos os zombies
    while ((entry = readdir(proc_dir)) != NULL) {
        // Verificar se é um diretório numérico (PID)
        // Usar atoi que retorna 0 para não-numéricos
        pid_t pid = atoi(entry->d_name);
        if (pid > 0 && zombie_count < 1024) {
            // verifica se é zombie e obtém info em uma única leitura
            if (get_zombie_info(pid, &zombies[zombie_count])) {
                zombie_count++;
            }
        }
    }
    
    closedir(proc_dir);
    
    for (int i = 0; i < zombie_count; i++) {
        fprintf(log_file, "%d %d %s\n", zombies[i].pid, zombies[i].ppid, zombies[i].comm);
    }
    fprintf(log_file, "==========================================\n");
    fflush(log_file);
}

// Função para configurar handlers de sinais
void setup_signal_handlers() {
    struct sigaction sa_term, sa_ignore;
    
    // Configurar handler para SIGTERM
    memset(&sa_term, 0, sizeof(sa_term));
    sa_term.sa_handler = sigterm_handler;
    sigemptyset(&sa_term.sa_mask);
    sa_term.sa_flags = 0;
    sigaction(SIGTERM, &sa_term, NULL);
    
    // Configurar handler para ignorar outros sinais
    memset(&sa_ignore, 0, sizeof(sa_ignore));
    sa_ignore.sa_handler = ignore_signal;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    
    // Ignorar sinais comuns (exceto SIGKILL e SIGSTOP que não podem ser capturados)
    sigaction(SIGHUP, &sa_ignore, NULL);
    sigaction(SIGINT, &sa_ignore, NULL);
    sigaction(SIGQUIT, &sa_ignore, NULL);
    sigaction(SIGPIPE, &sa_ignore, NULL);
    sigaction(SIGALRM, &sa_ignore, NULL);
    sigaction(SIGUSR1, &sa_ignore, NULL);
    sigaction(SIGUSR2, &sa_ignore, NULL);
    sigaction(SIGCHLD, &sa_ignore, NULL);
    sigaction(SIGCONT, &sa_ignore, NULL);
    sigaction(SIGTSTP, &sa_ignore, NULL);
    sigaction(SIGTTIN, &sa_ignore, NULL);
    sigaction(SIGTTOU, &sa_ignore, NULL);
}

int main(int argc, char *argv[]) {
    FILE *log_file;
    int interval;
    char message[256];
    
    // Verificar argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <intervalo_em_segundos>\n", argv[0]);
        return 1;
    }
    
    interval = atoi(argv[1]);
    if (interval <= 0) {
        fprintf(stderr, "Erro: O intervalo deve ser um número positivo\n");
        return 1;
    }
    
    // Abrir arquivo de log
    log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Erro ao abrir arquivo de log");
        return 1;
    }
    
    // Configurar handlers de sinais
    setup_signal_handlers();
    
    // Mensagem de início
    snprintf(message, sizeof(message), 
             "Monitor de processos zombies iniciado (PID: %d, Intervalo: %d segundos)", 
             getpid(), interval);
    write_debug_log(log_file, message);
    printf("%s\n", message);
    printf("Monitor em execução.\n");
    printf("Use 'kill -TERM %d' para finalizar.\n\n", getpid());
    
    fprintf(log_file, "PID PPID Nome do Programa\n");
    fprintf(log_file, "==========================================\n");
    fflush(log_file);
    
    // Loop principal
    while (keep_running) {
        write_debug_log(log_file, "Iniciando varredura de processos zombies");
        scan_zombies(log_file);
        // Dormir pelo intervalo especificado
        for (int i = 0; i < interval && keep_running; i++) {
            sleep(1);
        }
    }
    
    // Mensagem de finalização
    fprintf(log_file, "\nSIGTERM recebido. Monitor de processos zombies finalizado com sucesso.\n");

    fclose(log_file);
    return 0;
}
