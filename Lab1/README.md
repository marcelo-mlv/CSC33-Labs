# Laboratório 1

Este repositório contém os arquivos para a prática de laboratório da disciplina CSC-33.

## Descrição

...

## Comandos Disponíveis no Make

Aqui estão os comandos possíveis que podem ser executados com o Make a partir do [Makefile](./Makefile):

- `make build`: Compila o projeto.
- `make clean`: Remove os arquivos gerados durante a compilação.
- `make run`: Executa o programa após a compilação.
- `make test`: Executa os testes do projeto para verificar sua funcionalidade.

## Como Instalar o Make

Para instalar o Make ou certificar-se de que ele está instalado, siga as instruções abaixo:

### Verificar se o Make está instalado
Execute o seguinte comando no terminal:

```
make --version
```

Se o comando retornar a versão do Make, ele já está instalado no seu sistema.

### Instalar o Make
Caso o Make não esteja instalado, siga as instruções para o seu sistema operacional:

- **Ubuntu/Debian**:
  ```
  sudo apt update
  sudo apt install make
  ```

- **Fedora**:
  ```
  sudo dnf install make
  ```

- **MacOS**:
  O Make geralmente está incluído no Xcode Command Line Tools. Para instalar, execute:
  ```
  xcode-select --install
  ```

- **Windows**:
  Baixe e instale o Make (pela internet ou por alguma IDE) ou use o WSL (Windows Subsystem for Linux).
