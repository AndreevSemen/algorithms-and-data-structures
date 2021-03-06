# Бинарная упаковка колоды карт

Каждую карту можно описать с помощью ее масти и достоинства.
Чтобы описать перетасованную колоду, необходимо описать положение 52 карт.

Я предлогаю кодировать колоду карт следующим образом:

1. Масть карты кодируется 2 битами (так как всего 4 масти)
2. Достоинство кодируется 4 битами (всего у карт 13 достоинств)
3. Отдельно кодируем последовательность из 52 мастей
4. Отдельно кодируем последовательность из 52 достоинств

Получаем следубющую вместимость в 1 байт:

- В каждый байт вмещается ровно 4 масти
- В каждый байт вмещается ровно 2 достоинства

Тогда общая картина такая:

- Последовательность из 13 байт под все масти (`52/4`)
- Последовательность из 26 байт под все достоинства (`52/2`)

Общий объем закодированной колоды составляет: `13+26=39 байт`
или `312 бит`, то есть `6 бит/карту`
