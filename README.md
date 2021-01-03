# template-render-wizard

Application for rendering from template files, providing with values in yaml-files or by pass key-value for template with argument `--set key=value`.

## template language

#### render value
simple insert variable from yaml or argument passed
```
{{ variable_name }}
```
calculated value:
```
{% (variable_name + 5) * (variable_name - 5) %}
```
extract value from object:
```
{{ user.name }}
```

#### conditions
simple conditions
```
{% if expr %}
  ... < some code > ...
{% endif %}
```
conditions with else block
```
{% if expr %}
  ... < some code > ...
{% else %}
  ... <some code > ...
{% endif %}
```
#### expressions in if
simple check exists variable:
```
{% if some_variable %}
```
complex calculated conditions:
```
{% if x > y and y * (x - 1) < 50 %}
```

#### loops
simple:
```
{% for item in items %}
  ... <some code > ...
{% endfor %}
```
loop with key-value:
```
{% for key, val in items %}
  ... <some code > ...
{% endfor %}
```

### project dependencies
Static libraries:
  - [io-buffer](https://github.com/Alexander1000/io-buffer)
  - [cpp-unit-test](https://github.com/Alexander1000/cpp-unit-test) (for tests)
  - [yaml-parser](https://github.com/Alexander1000/yaml-parser) (parse values files)
  - [syntax-tree](https://github.com/Alexander1000/syntax-tree) (syntax tree)
  
## how it build?
```shell
cmake .
make
```

## examples
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
