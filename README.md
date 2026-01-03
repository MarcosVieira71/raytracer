# raytracer


Este projeto foi uma implementação educacional baseada no livro Ray Tracing in One Weekend (https://raytracing.github.io/books/RayTracingInOneWeekend.html), com o objetivo de estudar os fundamentos de ray tracing, materiais, iluminação e paralelização em CPU.

Além da implementação básica proposta no livro, o projeto foi estendido para:
- Renderização progressiva em janela (SDL)
- Paralelização com OpenMP
- Execução do render em thread separada para manter a UI responsiva

# Instalar dependências
conan install . \
    --output-folder=build \
    --build=missing

# Configurar o projeto
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release

# Compilar
cmake --build build

# Executar

./build/raytracer
