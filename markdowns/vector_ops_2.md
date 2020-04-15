#  Memória do dispositivo usando buffers e acessadores

## Configurando a memória do dispositivo - **Buffers**

### Descrição

Para manipular dados na memória do dispositivo, precisamos criar buffers SYCL.

O construtor para buffers para um ponteiro de dados brutos para os dados a serem gerenciados é o seguinte:

```cpp
cl::sycl::buffer<typename T, int dimensions>(
    T* ptr, 
    cl::sycl::range<dimensions>(int range_size)
);
```

### Tarefas

Crie buffers para os 2 vetores de entrada e também para o de saída.

Localização no código fonte:

```cpp
// <<Setup device memory>>
```

<details><summary>Dica</summary>
<p>

```cpp
// buffer for input 1
sycl::buffer<sycl::float4, 1> buf_a(&a, cl::sycl::range<1>{1});
```

</p>
</details>

## Acessando a memória do dispositivo - **Accessors**

### Descrição

O SYCL tem o conceito de acessadores que são usados para acessar o controle de solicitação sobre a memória do dispositivo a partir dos objetos buffer.

Os diferentes modos de acesso são encapsulados na seguinte classe enum:

```cpp
enum class mode { 
  read,
  write, 
  read_write, 
  discard_wirte, 
  discard_read_write,
  atomic
};
``` 
que mora no namespace `access`.

Nesta fase, focaremos apenas os mais comuns: `read`, `write` e `read_write`.

Um acessador SYCL pode ser criado a partir de um buffer usando a seguinte construção:

```cpp
// e.g., read access to buffer memory
auto sycl_acc = sycl_buf.get_access<cl::sycl::access::mode::read>(cgh)
```

onde `cgh` é uma instância do objeto manipulador do grupo de comandos SYCL `cl::sycl::handler`. É necessário que os acessadores sejam criados dentro do grupo de comandos para o qual serão usados.

### Tarefas

Solicite acesso dos buffers para acessar os dados no dispositivo.
- Acesso de leitura dos buffers de entrada
- Acesso de gravação do buffer de saída

Localização no código fonte:

```cpp
// <<Request device memory access>>
```

<details><summary>Dica</summary>
<p>

```cpp
// read accessor for the memory in `buf_a`
auto a_acc = buf_a.get_access<sycl::access::mode::read>(cgh);
```

</p>
</details>

# Vamos executar!

@[Olá mundo em SYCL]({"stubs": ["src/exercises/vector-ops_2.cpp"],"command": "sh /project/target/run.sh vector-ops_2", "layout": "aside"})
