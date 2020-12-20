This is test with parent context pass
Root based context values: ({{ key }}; {{ val }})
List elements:
{% for key, val in elements %}
    First loop values ({{ key }}; {{ val }})
    Loop:
    {% for key, val in elements %}
        Nested loop values ({{ key }}; {{ val }})
    {% endfor %}
    Loop with another data:
    {% for k, v in els %}
        Parent loop values ({{ key }}; {{ val }})
        Current loop values ({{ k }}; {{ v }})
    {% endfor %}
{% endfor %}
After loops root based context values: ({{ key }}; {{ val }})
