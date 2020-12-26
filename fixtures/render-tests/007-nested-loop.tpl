<div>
{% for article in articles %}
    <article>
        <h1>{{ article.title }}</h1>
        <p>{{ article.description }}</p>
        <div>
            {% for photo in article.photos %}
                <div>
                    <h2>{{ photo.name }}</h2>
                    <ul>
                        {% for size in photo.sizes %}
                            <li>{{ image.prefix }}/{{ size }}</li>
                        {% endfor %}
                    </ul>
                </div>
            {% endfor %}
        </div>
    </article>
{% endfor %}
</div>
