# Metrics Logger

**Тестовое задание для стажировки ВКонтакте**

## Как собрать

Требования:

- C++17 компилятор (g++ >= 7, clang++ >= 5)
- CMake >= 3.10

Сборка проекта:

```bash
mkdir build
cd build
cmake ..
make
```

## Как пользоваться

```auto& registry = MetricsRegistry::instance()``` - создание объекта для записи.
```registry.registerMetric<T>(name_metric)``` - чтобы добавить метрику для ее последующей
записи в файл нужно передать тип(T) и название(name_metric) в метод объекта

```MetricsFlusher flusher(name_metric, time_ms_w)``` - создаем флашер, передаем название файла и 
периодичность в милисекундах для самой записи

```registry.record(name_metric, value);``` - передаем значение конкретной метрики и записываем.

