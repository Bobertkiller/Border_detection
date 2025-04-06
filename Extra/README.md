## Trechos Essenciais

### 1. Inicialização SDL (edge_detection.c)
```c
SDL_Window* window = SDL_CreateWindow("Detector de Bordas", 800, 600, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
```
Este trecho de código inicializa a biblioteca SDL, criando uma janela com o título "Detector de Bordas" e um renderer acelerado para renderização gráfica.

### 2. Detecção de Bordas (edge_detection.c)
```c
float gx = (-1 * get_pixel(img, x-1, y-1)) + (1 * get_pixel(img, x+1, y-1)) + ...;
float gy = (-1 * get_pixel(img, x-1, y-1)) + (-2 * get_pixel(img, x, y-1)) + ...;
Uint8 gradient = (Uint8)sqrt(gx * gx + gy * gy);
```
Neste trecho, o operador Sobel é aplicado para calcular os gradientes nas direções X e Y. A magnitude do gradiente é então calculada, que é usada para determinar a intensidade das bordas na imagem.

### 3. Manipulação de Pixels (edge_detection.h)
```c
#define get_pixel(surface, x, y) (((Uint32*)surface->pixels)[y * surface->w + x])
```
Esta macro permite acessar os pixels de uma superfície SDL de forma eficiente, convertendo os dados de pixels em um ponteiro para `Uint32` e calculando o índice correto com base na largura da superfície.

###  Diagrama do Fluxo

[Imagem BMP] → [SDL_LoadBMP] → [detect_edges()] → [SDL_Texture] → [Janela SDL]

Este diagrama ilustra o fluxo de dados desde a imagem BMP carregada até a exibição na janela SDL após a detecção de bordas.

