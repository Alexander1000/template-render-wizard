User account balance: {{ user.money.total }}
User capacity: {{ user.cart.capacity }}
User used: {{ user.cart.used }}
Shop items:
{% for id, item in items %}
<item>
    <id>{{ id }}</id>
    <title>{{ item.name }}</title>
    <price>{{ item.price }}</price>
    <size>{{ item.size }}</size>
</item>
Can buy it? - {% if user.money.total > item.price and item.size <= user.cart.capacity - user.cart.used %}Yes{% else %}No{% endif %}
{% endfor %}
