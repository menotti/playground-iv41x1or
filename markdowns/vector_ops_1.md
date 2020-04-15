# Configuração do host e fila (Queue) SYCL

Este exercício é uma versão ligeiramente modificada da adição de vetor que fizemos no exemplo anterior. Você assumirá o controle deste e concluirá o código para essa aplicação sozinho. São fornecidas instruções em cada etapa da conclusão, portanto, você deve ser capaz de fazê-lo. Vamos começar.

> Até agora, você deve saber que precisa incluir o arquivo de cabeçalho SYCL para usar o SYCL em sua aplicação. Ele já está incluído na parte superior do arquivo de origem - `#include <CL/sycl.hpp>`.

## Configuração do host

### Descrição

O primeiro passo é inicializar os dados vetoriais no host.

Nós estaremos usando:

```cpp
cl::sycl::float4
```
que é um alias de tipo para

```cpp
cl::sycl::vec<float, 4>
```

É uma estrutura do tipo SYCL que fornece a funcionalidade do vetor OpenCL para _host_ e dispositivo.

### Tarefa

Defina 2 vetores de entrada e 1 vetor de saída.

Entradas:
 - vetor `a`: `{1.0, 1.0, 1.0, 1.0}`
 - vetor `b`: `{1.0, 1.0, 1.0, 1.0}`

Resultado:
- vetor `c`: `{0.0, 0.0, 0.0, 0.0}`

Localização no código fonte:

```cpp
// <<Setup host memory>>
```

<details><summary>Dica</summary>
<p>

```cpp
sycl::float4 a = { 1.0f, 1.0f, 1.0f, 1.0f }; // entrada 1
```

</p>
</details>

## Inicializar fila SYCL

### Descrição

A fila SYCL é construída a partir da seleção de um dispositivo suportado.

O sistema está configurado para sempre forçar a execução dos exemplos SYCL no dispositivo da CPU. Assim, o seletor padrão selecionará a CPU devido às suas heurísticas para identificar as plataformas e dispositivos suportados em nosso sistema.

### Tarefa

Inicialize uma fila SYCL com uma CPU ou seletor de dispositivo padrão.

Localização no código fonte:

```cpp
// <<Setup SYCL queue>>
```

<details><summary>Hint</summary>
<p>

```cpp
sycl::queue myQueue(sycl::default_selector{}); 
// seleciona explicitamente a CPU: sycl::cpu_selector{}
```

</p>
</details>

# Vamos executar!

@[Olá mundo em SYCL]({"stubs": ["src/exercises/vector-ops_1.cpp"],"command": "sh /project/target/run.sh vector-ops_1", "layout": "aside"})
