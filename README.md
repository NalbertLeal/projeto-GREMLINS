# Predição de salto

### tópicos abordados:  
  
- **A implementação**;
- **Como compilar e executar**
- **Testes realizados**;
- **Bugs**;
- **Observações**;
- **Sobre mim**;

##### status do projeto: **Em desenvolvimento**  
    
#### Introdução  
  Este projeto implementa um gerenciador de memória em c++. Será utilizado por codigos escritos em c++ para fazer todo o manejamento de memória não deixando a cargo do programador criar ou deletar dados da memória alocada dinamicamente.

### O projeto
Esse projeto está sendo desenvolvido como uma atividade do semestre 2016.1 da turma de EDB1 e LP1 do professor Selan Rodrigues, um gerenciador de memória que maneja a memoria alocada dinâmica será implementada em c++. O projeto está sendo implementado tomando como base os requerimento do que se pede no arquivo pdf enviado pelo professor.
   
#### A implementação:  
  
  Os seguintes arquivos são pertencentes a implementação da predição até o momento:
  
  1) **src/drive_hash_Version3.hpp** : Contém o codigo da função main
  2) **include/DoisBin.hpp** :  Contém a classe DoisBin.
  3) **include/DoisBin.inl** : Contém a implentação dos métodos da classe DoisBin.
  4) **Doxygen** :  Arquivo de configuração para gerar a documentação do codigo com o doxygen.
  
### Como compilar e executar
  Para compilar o código é indicado o compilador g++ pois esse foi o programa utilizado na compilação do codigo. Assumindo que os requerimentos/conselhos estejam sendo seguidos para compilar o codigo do vector usando o g++ é necessario utilizar o seguinte comando no terminar dentro da pasta Vector:
  
    g++ -std=c++11 -I include src/main.cpp -o bin/gremlins
  
  Também pode se utilizar o makefile, basta digitar o comando a seguir que o código será compilado:
  
    make
  
  O arquivo gerado se encontra dentro da pasta bin do diretorio do projeto e possui o nome gremlins. Para executar o arquivo basta entrar na pasta bin e digitar ./gremlins para ver um exemplo do uso do gerenciador de memória implementado.  

### Testes realizados:
  
  Os testes realizados foram feitos com base no que pede o pdf enviado pelo professor Selan. Esses testes podem não refletir algum eventual bug que testes profundos no codigo revelariam.
    
### Bugs:
  
  Os testes realizados não revelaram algum erro. Entretanto isso não significa que o programa está livre de erros.

### Observações:

  O codigo será postado no GitHub para posiveis avaliações futuras. O projeto é muito interessante e pode ter suas ideias fundamentais sendo utilizadas base para diversos projetos futuros.

  Esse projeto se encontra no Git Hub no link:  
   [link do projeto](https://github.com/nalbertg/projeto-GREMLINS)


### Sobre mim:
    
- **Aluno**: Nalbert Gabriel Melo Leal;  
- **GitHub**: github.com/nalbertg ;  
- **email pessoal**: nalbertrn@yahoo.com.br;  
- **email acadêmico/profissional**: nalbertg@outlook.com;  
  
