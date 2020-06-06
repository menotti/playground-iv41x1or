# Introdução ao SYCL<sup id="a1">[1](#f1)</sup>

## O que é SYCL?

O SYCL (pronuncia-se 'sicou') é uma camada de abstração multiplataforma, isenta de royalties, que se baseia nos conceitos subjacentes, portabilidade e eficiência do OpenCL, permitindo que o código para processadores heterogêneos seja gravado no estilo “single-source” (código fonte único) usando somente C++ padrão. O SYCL permite o desenvolvimento com um único código fonte, em que as funções de _templates_ C++ podem conter código de _host_ e dispositivo para construir algoritmos complexos que usam a aceleração OpenCL e, em seguida, reutilizá-los em todo o código-fonte em diferentes tipos de dados.

O SYCL é totalmente C++ padrão, portanto, não há extensões ou atributos de idioma necessários.

Este tutorial tem como objetivo ensinar os fundamentos do SYCL por meio da explicação de uma aplicação simples.

Usaremos o ComputeCpp, uma implementação compatível com SYCL v1.2.1 para compilar e executar os exemplos.

<b id="f1">1</b> Este tutorial faz parte de um [Curso de Programação Paralela](https://github.com/menotti/pp) e traz apenas exemplos de uso. Acesse o material completo para mais detalhes. [↩](#a1)