<html>
<head></head>
<body>
{% for item in items %}
<div>
    <p>[Simple] {{ title }}: {{ item.title }}</p>
    {% include "__include/item.tpl" with {
        price: (item.price - 10) * 11 - (item.price + 10) * 10,
        isAvailable: user.age >= item.minAvailableAge
    } %}

    <p>[Only] {{ title }}: {{ item.title }}</p>
    {% include "__include/item.tpl" with {
        price: (item.price - 10) * 11 - (item.price + 10) * 10,
        isAvailable: user.age >= item.minAvailableAge
    } only %}
</div>
{% endfor %}
</body>
</html>
