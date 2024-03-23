# Interface Sensor DHT

Interface para um computador embarcado para medição de temperatura ambiente e umidade relativa do ar.

O projeto foi feito em C++ com Qt6 e QML.

## Instalação e Execução

Detalhes dos passos a seguir

### Requisitos

- CMake
- GCC/G++
- Qt6
- Arduino IDE
 - OBS: Pode usar outras IDEs (MPLABX por exemplo) ou um compilador para o ESP32).

Do Qt6 é necessário ter instalado as bibliotecas:

- Serial Port
- Bluetooth
- Web Service e relacionadas

### Instruções

1. Clone o repositório:
```
git clone https://github.com/lucasfturos/InterfaceSensorDHT.git
```

2. Crie a pasta build usando cmake:
```
cmake -S . -B build
```

3. Construa o projeto:
```
cmake --build build
```

4. Execute o programa:
```
./build/appInterfaceSensorDHT
```

5. Gerar a documentação:
```
cmake --build build --target documentation
```
