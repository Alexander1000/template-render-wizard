Example with reorder root element in context.
Based value of key: "{{ key }}" and value of val: "{{ val }}"
List elements:
{% for key, val in items %}
    - key: {{ key }}; val: {{ val }}
{% endfor %}
After loop this values get from root context:
Based value of key: "{{ key }}" and value of val: "{{ val }}"
