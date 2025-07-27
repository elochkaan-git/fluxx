# Компьютерная версия настольной карточной игры Fluxx

## Linux сборка
Установка зависимостей:
```
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
```
debian based:
```
sudo apt-get install libfreetype6-dev
```

## Запуск build'а
Очень важно запускать программу из корневой папки:
```
cd path/to/fluxx/
./bin/main
```

## Авторы
Савелий Бурковский (Smahhunter) - фронтенд
Александр Елышкин (Elochkaan) - бэкэнд