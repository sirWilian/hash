# hash
###### O projeto busca implementar tabelas hash de endereçamento aberto com tratamento de colisão feito em uma tabela extra utilizando linguagem C.

para compilar o projeto, você deve instalar o compilador gcc, mas caso esteja utilizando algum sistema UNIX, tudo que você deve fazer é utilizar o comando "**make**" dentro do diretório.

para executar o programa:

``` bash
 ./myht < entrada.txt > saida.txt
```
onde o arquivo "entrada.txt" (ou qualquer formato simples de texto) deve conter a operação a ser feita e o número a ser guardado:
```
i 10
i 22
i 4
i 15
i 59
r 15
r 22
r 59

```
o arquivo "saida.txt" mostrará a chave, tabela e posição em que o número ficou armazenado.
no exemplo acima, a saída será:
```
4,T2,6
10,T1,10

```

para limpar os arquivos criados ao compilar o programa, utilize:

``` bash
make purge
```

