# Aplicação de Detecção de Bordas

## Visão Geral
Esta aplicação demonstra a detecção de bordas em imagens digitais usando técnicas de visão computacional. Construída com C e SDL3, ela identifica e destaca as fronteiras entre diferentes regiões nas imagens, focando nas descontinuidades em brilho, cor e textura.

## Recursos
- Detecção de bordas usando o operador Sobel
- Visualização em tempo real das bordas detectadas
- Limite ajustável para a sensibilidade da detecção de bordas
- Interface simples e intuitiva para carregamento e exibição de imagens

## Contexto Técnico
A aplicação implementa a detecção de bordas com base nos seguintes princípios:

- **Bordas** existem onde ocorrem mudanças abruptas em uma imagem (transições de luz/sombra, limites de materiais, contornos de objetos)
- **Descontinuidades** são detectadas em:
  - Normais de superfície
  - Profundidade
  - Cor da superfície
  - Iluminação
- As mudanças são calculadas usando derivadas parciais, tratando as imagens como funções matemáticas.

## Estrutura do Projeto
```
border_detection/
├── src/           # Source code files
│   └── edge_detection.c
├── include/       # Header files
│   └── edge_detection.h
├── build/         # Build artifacts
├── assets/        # Test images
│   └── test_image.bmp
└── Makefile
```


## Dependências
- Biblioteca SDL3
- Compilador C (gcc recomendado)
- make

## Compilando o Projeto
```bash
# Criar diretórios do projeto
mkdir -p build assets

# Compilar a aplicação
make

# Executar com uma imagem de teste
make run_with_image
```

## Uso
```bash
# Executar com uma imagem específica
./build/border_detection caminho/para/sua/imagem.bmp
```

### Controles
- **ESC**: Sair da aplicação

## Algoritmo
A implementação usa o operador Sobel para detecção de bordas:

1. Converter a imagem de entrada para escala de cinza
2. Aplicar o operador Sobel nas direções X e Y
3. Calcular a magnitude do gradiente
4. Aplicar um limite para determinar os pixels de borda

## Exemplo
Imagem original → Detecção de bordas → Resultado com bordas visíveis destacando as fronteiras entre regiões com diferentes propriedades.

## Limitações
- Atualmente suporta imagens BMP nativamente
- Para outros formatos (PNG, JPEG), a extensão SDL_image seria necessária

## Melhorias Futuras
- Algoritmos adicionais de detecção de bordas (Canny, Prewitt, LoG)
- Ajuste de parâmetros em tempo real via controles da interface
- Suporte para mais formatos de imagem
- Processamento em lote de várias imagens