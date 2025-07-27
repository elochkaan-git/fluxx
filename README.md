# Компьютерная версия настольной карточной игры Fluxx

Компьютерная версия настольной карточной игры Fluxx

## Описание

Игра представляет собой компьютерную версию настольной карточной игры Fluxx, написанную на языке программирования C++ с использованием SFML/TGUI для отрисовки. На данный момент поддерживается лишь поочередная игра за одним компьютером, а также реализованы только карты тем и целей.

## Установка и запуск

Требования:

- С++17 и выше
- Cmake 3.28 и выше

Клонирование репозитория:

```bash
git clone https://github.com/elochkaan-git/fluxx.git
cd fluxx
```

Установка зависимостей:
```bash
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype6-dev
```

Сборка проекта:

```bash
cmake -S . -B ./build && cmake --build ./build
```

Запуск приложения:

```bash
./bin/main
```

## Авторы

Савелий Бурковский (Smahhunter) - фронтенд
Александр Елышкин (Elochkaan) - бэкэнд
