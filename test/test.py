import pytest
from utils.helpers import *

def test_isolate_words():
   assert isolate_words(['cancion', '_', 'original'], 1) == ['cancion', 'original']
   assert isolate_words(['cancion', 'muy', '_'], 1) == ['muy']
   assert isolate_words(['_', 'muy', 'original'], 1) == ['muy']
   assert isolate_words(['cancion', '_', 'super', 'original'], 2) == ['original']
   assert isolate_words(['_', 'supertest'], 1) == ['supertest']

def test_add_words():
    assert add_words(["soy", "una", "letra", "de", "una", "cancion", "y", "es", "por", "eso"], ["una"], ["_", "una", "frase"]) == {"de": 1, "soy": 1}
    assert add_words(["letra", "de", "cancion", "de", "charly", "garcia"], ["de"], ["soy", "una", "frase", "de", "_"]) == {"cancion": 1, "charly": 1}
    assert add_words(["letra", "de", "cancion", "de", "charly", "garcia"], ["una", "de"], ["soy", "una", "_", "de", "charly"]) == {"cancion": 1, "letra": 1}

def test_get_keys_max_val():
    assert get_keys_max_val({"palabra": 2, "muy": 1, "usada": 1, "prueba": 3}) == ["prueba"]
    assert get_keys_max_val({"palabra": 3, "muy": 1, "usada": 1, "prueba": 3}) == ["palabra", "prueba"]
    assert get_keys_max_val({"palabra": 3}) == ["palabra"]

def test_format_text_phrase():
    assert format_text_phrase(["Hola", "soy", "un", "test.", "Que", "busca", "romper", "el", "_,"]) == ["hola", "soy", "un", "test", "que", "busca", "romper", "el", "_"]
    assert format_text_phrase(["Hola", "soy", "un,", "test.", "Que", "busca", "romper", "el", "_."]) == ["hola", "soy", "un", "test", "que", "busca", "romper", "el", "_"]