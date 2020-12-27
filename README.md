# template-render-wizard

Application for rendering from template files, providing with values in yaml-files.

### project dependencies
Static libraries:
  - [io-buffer](https://github.com/Alexander1000/io-buffer)
  - [cpp-unit-test](https://github.com/Alexander1000/cpp-unit-test) (for tests)
  - [yaml-parser](https://github.com/Alexander1000/yaml-parser) (parse values files)
  
### how it build?
```shell
cmake .
make
```

### examples
For example content of values file:
```yaml
# data for tests (fixtures/003-values.yaml)
name: test-data
```

Template file:
```txt
Hello world!
My name is {{ name }}!
```

Run application and his output:
```shell
./template-render-wizard --values fixtures/003-values.yaml fixtures/003-simple-text.txt
Hello world!
My name is test-data!

```
