<html>
<head>
    <title>{{ site.title }}{% if user.name %}[{{ user.name }}]{% endif %}</title>
</head>
<body>
    <h1>Hello on {{ site.name }}</h1>
    <div>
        {% if user.auth %}
            <a href="/logout">Выйти{% if user.name %}[{{ user.name }}]{% else %}Anonymous{% endif %}</a>
        {% else %}
            Go to login page: <a href="/login">Login</a>
            {% if site.redesign %}
                <div>{{ site.content }}</div>
            {% endif %}
        {% endif %}
    </div>
</body>
</html>
