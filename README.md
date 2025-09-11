# Minishell

## Lista de tareas (TO DO)

- [✅] **Mostrar una entrada** mientras espera un comando nuevo.
- [✅] **Tener un historial funcional.**
- [✅] Buscar y ejecutar el ejecutable correcto (basado en la variable `PATH` o mediante el uso de rutas relativas o absolutas).
- [✅] No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como `\` (barra invertida) o `;` (punto y coma).
- [✅] Gestionar que la `'` evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
- [✅] Gestionar que la `"` evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando `$` (signo de dólar). <-- [✅]
- **Implementar redirecciones:**
  - `<` debe redirigir input. [✅]
  - `>` debe redirigir output. [✅]
  - `<<` debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial. [✅]
  - `>>` debe redirigir el output en modo append. [🔁]
- [✅] **Implementar pipes** (carácter `|`). El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando.
- [✅] Gestionar las **variables de entorno** (`$` seguidos de caracteres) que deberán expandirse a sus valores.
- [🔁] Gestionar `$?`, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.
- Gestionar señales que funcionan como en bash:
  - `ctrl-C` [✅]
  - `ctrl-D` [✅]
  - `ctrl-\` [🔁]
- Cuando sea interactivo:
  - `ctrl-C` imprime una nueva entrada en una línea nueva. [✅]
  - `ctrl-D` termina el shell. [✅]
  - `ctrl-\` no hace nada. [🔁]
- **Implementar los built-ins:**
  - `echo` con la opción `-n`. [✅]
  - `cd` solo con una ruta relativa o absoluta. [✅]
  - `pwd` sin opciones. [✅]
  - `export` sin opciones. [✅]
  - `unset` sin opciones. [✅]
  - `env` sin opciones o argumentos. [✅]
  - `exit` sin opciones. [🔁]

---

> **Minishell**  
> Tan bonito como shell
> Nos queda solo mirar las exit status y ver si en utils los signals estan bien :D



/*
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *tokens;
    t_ms ms;
	ms.exit_status = 0; 

    char cwd[4096];
    char hostname[256];
    char *prompt;
    char *user;
    struct passwd *pw;


    ms.envp = copy_envp(envp);
    ms.env_list = init_env_list(envp);
	setup_signals();
    while (1)
    {
        pw = getpwuid(getuid());
        if (pw && pw->pw_name)
            user = pw->pw_name;
        else
            user = "user";

        if (gethostname(hostname, sizeof(hostname)) != 0)
            ft_strcpy(hostname, "minishell");

        char *pwd_env = get_env_value(ms.env_list, "PWD");
        if (pwd_env)
            ft_strlcpy(cwd, pwd_env, sizeof(cwd));
        else if (!getcwd(cwd, sizeof(cwd)))
            ft_strcpy(cwd, "~");

        char *home = getenv("HOME");
        char *display_cwd = cwd;
        int display_malloced = 0;

        if ((home && ft_strcmp(cwd, home) == 0))
        {
            display_cwd = "~";
            display_malloced = 0;
        }
        else if (home)
        {
            size_t home_len = ft_strlen(home);
            if (ft_strncmp(cwd, home, home_len) == 0 && cwd[home_len] == '/')
            {
                size_t new_len = ft_strlen(cwd) - home_len + 2;
                char *tmp = malloc(new_len);
                if (tmp)
                {
                    tmp[0] = '~';
                    ft_strcpy(tmp + 1, cwd + home_len);
                    display_cwd = tmp;
                    display_malloced = 1;
                }
            }
        }

        size_t prompt_len = ft_strlen(user) + 1 + ft_strlen(hostname) + 1 + ft_strlen(display_cwd) + 3;
        prompt = malloc(prompt_len);
        if (!prompt)
            prompt = ft_strdup("$ ");
        else
            snprintf(prompt, prompt_len, "%s@%s:%s$ ", user, hostname, display_cwd);

        line = readline(prompt);
        free(prompt);
        if (display_malloced)
            free(display_cwd);
        if (!line)
        {
            printf("exit\n");
            exit(0);
        }
        if (*line)
        {
            add_history(line);
            tokens = lexer(line);
            if (tokens)
            {
                t_simple_cmds *cmds = NULL;
                parse_simple_cmds(&tokens, &cmds, &ms);

                if (cmds && cmds->next)
                    execute_pipeline(cmds, &ms);
                else if (cmds)
                {
                    // Si el comando es "exit", salimos inmediatamente
                    if (cmds->str && cmds->str[0] && ft_strcmp(cmds->str[0], "exit") == 0)
                    {
                        free_simple_cmds(cmds);
                        free(line);
                        printf("exit\n");
                        exit(0);
                    }
                    // Si es un builtin, ejecútalo en el padre
                    if (is_builtin(cmds->str[0]))
                    {           
						apply_redirections(cmds, &ms);	
                        ms.exit_status = handle_builds(cmds->str, &ms);
                    }
                    else
                    {
                        pid_t pid = fork();
                        if (pid == 0)
                        {
                            apply_redirections(cmds, &ms);
                            execvp(cmds->str[0], cmds->str);
                            perror("execvp");
                            exit(127);
                        }
                        else if (pid > 0)
                        {
                            int status;
                            waitpid(pid, &status, 0);
                        }
                    }
                }
                free_simple_cmds(cmds);
            }
        }
		free(line);
    }
    return 0;
}*/