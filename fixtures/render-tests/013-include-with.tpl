<html>
<head></head>
<body>
{% for item in items %}
<div>
    {% include "__include/item.tpl" with {
        title: item.title,
        price: (item.price - 10) * 11 - (item.price + 10) * 10,
        isAvailable: user.age >= item.minAvailableAge
    } %}
</div>
{% endfor %}
</body>
</html>
