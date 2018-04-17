# game-opengl-pg
Projeto de um game, destinado para realização do trabalho da disciplina de Processamento Gráfico, Unisinos 2018-1.

Alunos: Pablo; Savanna.

------------------------------------------------------------------------------------------------------------------

Como configurar o ambiente:

- Faça clone do projeto;
- Depure o projeto para verificar se a versao do core está de acordo como o modelo de seu computador, caso apareça erro de shader, modifique a versão do core na primeira linha dos arquivos 'transformations.frag' e 'transformations.vs', para uma inferior, exemplo: '#version 400 core', ou menor;
- Caso tenha problema com as dependencias, logo depois ao abrir o projeto no VS, faça a configuração do diretório das dependencias em:
  - Propriedades > C/C++ > Diretórios de Inclusão Adicionais > ... Adiciocione os diretórios 'GLEW/include e GLFW/include', e '/glm' da pasta /dependencies deste projeto;
  - Propriedades > Vinculador > Diretórios de Biblioteca Adicionais > ... Adiciocione os diretórios 'GLEW/lib e GLFW/lib' da pasta /dependencies deste projeto.
* Obs.: As propriedades do projeto já estão setadas para localizar e determinar as dependencias nos diretórios acima.
