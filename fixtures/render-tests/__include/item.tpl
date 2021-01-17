<div class="item">
    <h1>{{ title }}</h1>
    <p><b>Price:</b> {{ price }}</p>
    {% if isAvailable %}
        <button>Put in cart</button>
    {% endif %}
</div>
