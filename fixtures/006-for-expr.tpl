List items:
{% for item in items %}
 - [{{ item.name }}] - {{ item.price }} by {{ user.name }}
{% endfor %}
