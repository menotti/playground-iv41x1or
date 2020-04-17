# Começando com SYCL

## Como o SYCL funciona?

Uma implementação SYCL consiste em dois componentes principais: (i) um compilador de dispositivo SYCL, que compila seu código para dispositivos OpenCL, e (ii) uma biblioteca de tempo de execução SYCL que fornece a interface de alto nível para escrever aplicativos SYCL e o _runtime_ para executar o código do dispositivo em dispositivos OpenCL.

## Em que o SYCL é executado?

O SYCL pode atingir uma ampla variedade de dispositivos OpenCL em qualquer sistema, como CPUs com vários núcleos, GPUs, FPGAs, DSPs e outros tipos de aceleradores e processadores especializados. Por exemplo, o ComputeCpp, uma implementação compatível com SYCL 1.2.1, permite que o código SYCL seja executado na Intel, AMD, ARM, Renesas, NVIDIA e nos futuros processadores Imagination.

O pacote ComputeCpp fornece uma ferramenta chamada `computecpp_info`, que pode ser usada para várias coisas, mas principalmente para detectar dispositivos suportados no sistema que podem ser usados pelo ComputeCpp.

Para fins de demonstração, podemos executar o `computecpp_info` aqui para exibir os dispositivos OpenCL disponíveis para este tutorial.

Clique no botão `Run` para ver como é sua saída:

@[ComputeCpp Info]({"command": "sh /project/target/validate.sh"})

* Observe que este tutorial está sendo executado em uma instância de nuvem e, portanto, está usando uma CPU Intel, não há GPU ou processador acelerador disponível.

A linha principal para observar é esta

`Device is supported                     : YES - Tested internally by Codeplay Software Ltd.`
 
 traduzindo 
 
`O dispositivo é suportado               : SIM - Testado internamente pela Codeplay Software Ltd.`

Como você pode ver na saída de comando `computecpp_info`, o único dispositivo suportado é o "host", que é a CPU Intel. Embora seja improvável oferecer melhorias de desempenho na ausência de uma GPU, ele permite executar nosso código SYCL usando o ComputeCpp.
