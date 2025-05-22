# Minishell

## Lista de tareas (TODO)

- [✅] **Mostrar una entrada** mientras espera un comando nuevo.
- [✅] **Tener un historial funcional.**
- [❌] Buscar y ejecutar el ejecutable correcto (basado en la variable `PATH` o mediante el uso de rutas relativas o absolutas).
- [❌] No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como `\` (barra invertida) o `;` (punto y coma).
- [❌] Gestionar que la `'` evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
- [❌] Gestionar que la `"` evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando `$` (signo de dólar).
- **Implementar redirecciones:**
  - `<` debe redirigir input. [❌]
  - `>` debe redirigir output. [❌]
  - `<<` debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial. [❌]
  - `>>` debe redirigir el output en modo append. [❌]
- [❌] **Implementar pipes** (carácter `|`). El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando.
- [❌] Gestionar las **variables de entorno** (`$` seguidos de caracteres) que deberán expandirse a sus valores.
- [❌] Gestionar `$?`, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.
- Gestionar señales que funcionan como en bash:
  - `ctrl-C` [❌]
  - `ctrl-D` [❌]
  - `ctrl-\` [❌]
- Cuando sea interactivo:
  - `ctrl-C` imprime una nueva entrada en una línea nueva. [❌]
  - `ctrl-D` termina el shell. [❌]
  - `ctrl-\` no hace nada. [❌]
- **Implementar los built-ins:**
  - `echo` con la opción `-n`. [❌]
  - `cd` solo con una ruta relativa o absoluta. [❌]
  - `pwd` sin opciones. [❌]
  - `export` sin opciones. [❌]
  - `unset` sin opciones. [❌]
  - `env` sin opciones o argumentos. [❌]
  - `exit` sin opciones. [❌]

---

> **Minishell**  
> Tan bonito como shell