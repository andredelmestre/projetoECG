Estudos sobre transmissao e processamento de sinais ECG
===========================================
Estou trabalhando num projeto de pesquisa para adquirir, processar, enviar e visualizar sinais de eletrocardiograma (ECG). A equipe tem dois alunos, um professor de eletronica e eu. Neste repositorio estou compartilhando alguns dos meus estudos nesse tema.

# Contents
- [Programacao Estruturada](#projeto-em-programacao-estruturada)
- [Arduino](#arduino-folder)

## Projeto em Programacao Estruturada 

A disciplina de Programacao Estruturada eh oferecida nos cursos de Tecnologia de Sistemas para Internet (TSI) e Engenharia de Controle e Automacao (ECA) do [IFSul](http://www.ifsul.edu.br/) campus [Charqueadas](http://www.charqueadas.ifsul.edu.br/portal/).

A avaliacao dos alunos eh desenvolver um projeto num tema escolhido por eles envolvendo todos os topicos da disciplina: funcoes, recursao, ponteiros, strings, alocacao dinamica e manipulacao de arquivos

Para os alunos terem uma referencia, eu tambem estou desenvolvendo meu projeto. O Topico do meu projeto eh tratamento de sinais de eletrocardiograma (ECG)

Para entender o que esta sendo desenvolvido, assista [esse video](https://youtu.be/H8aN4utajPg).

Para assistir a apresentacao das funcoes e o programa funcionando, veja [esse video](https://youtu.be/KSDQYPWOiBE).

## Arduino Folder

Estamos desenvolvendo [servidor proprio](http://ecgremoto.herokuapp.com/) e precisamos enviar os dados coletados para este servidor utilizando protocolo HTTP.

O hardware para aquisicao do ECG esta em desemvolvimento e precisamos orientar a programacao de um modulo ESP8266 para comunicar com o nosso servidor.

Para compreender como realizar essas requisicoes web e poder dar suporte a programacao do ESP8266, desenvolvi um codigo para se comunicar com o nosso servidor e outros servidores para fins de aprendizado. 

Este codigo eh um aglomerado de inumeros tutoriais de internet e ainda esta em desenvolvimento. =)


## Requirements

Voce precisa ter o compilador [GCC](https://gcc.gnu.org/) para rodar os codigos escritos em linguagem C.

Compativeis com Linux e macOS. 

Para utilizar esses codigos no Windows sem GCC, assista [esse video](https://www.youtube.com/watch?v=h_m0vf6mt1E&list=PLeZ9_FbdLGk7K4ma8oXb3hhcjBMjF1Kcp&index=2).

## Content
Aqui voce encontra:

`plot` - Arquivos de ECG e plot dos ECG coletados do repositorio physionet

`code` - codigos em C trabalhados na aula e em videos assincronos com as turmas TSI e ECA

`arduino` - codigo compativel com Arduino IDE com o objetivo de enviar dados de ECG de um arquivo para diferentes clouds via protocolo HTTP


## Usage

```bash
# go to a dir containing C codes.
cd code
# compiles and generates executable program
make prog
# executes the program
./prog
# clear compiling files and the .exe file
make clear
```

## Support

Website at [http://tsi.charqueadas.ifsul.edu.br/~delmestre/](http://tsi.charqueadas.ifsul.edu.br/~delmestre/)

E-mail at [almmartins@charqueadas.ifsul.edu.br](almmartins@charqueadas.ifsul.edu.br)
 or at [almmartins@acad.charqueadas.ifsul.edu.br](almmartins@acad.charqueadas.ifsul.edu.br)

