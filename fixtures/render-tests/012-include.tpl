<html>
<head></head>
<body>
{% for user in users %}
    <block>
        {% include "004-text-with-condition.tpl" %}
    </block>
{% endfor %}
</body>
</html>
