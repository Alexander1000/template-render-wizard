# template-render-wizard

Application for rendering from template files, providing with values in yaml-files.

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
