# Introdução ao SYCL

## O que é SYCL?

O SYCL (pronuncia-se 'saicou') é uma camada de abstração multiplataforma, isenta de royalties, que se baseia nos conceitos subjacentes, portabilidade e eficiência do OpenCL, permitindo que o código para processadores heterogêneos seja gravado no estilo “single-source” (código fonte único) usando somente C++ padrão. O SYCL permite o desenvolvimento com um único código fonte, em que as funções de _templates_ C++ podem conter código de _host_ e dispositivo para construir algoritmos complexos que usam a aceleração OpenCL e, em seguida, reutilizá-los em todo o código-fonte em diferentes tipos de dados.

O SYCL é totalmente C++ padrão, portanto, não há extensões ou atributos de idioma necessários.

Este tutorial tem como objetivo ensinar os fundamentos do SYCL por meio da explicação de uma aplicação simples.

Usaremos o ComputeCpp, uma implementação compatível com SYCL v1.2.1 para compilar e executar os exemplos.
