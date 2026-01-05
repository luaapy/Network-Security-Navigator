# NSN Grammar and Parsing

This directory contains the formal grammar definition for the NSN language.

## Files
- `nsn.gram`: The PEG (Parsing Expression Grammar) definition.
- `Tokens`: List of lexical tokens recognized by the lexer.
- `test_grammar.py`: Utility script to validate the grammar against sample inputs.

## Parser Generation
The parser is generated from `nsn.gram` using the `Tools/peg_generator` (pegen).
During development, a hand-written recursive descent parser in `Parser/` may be used for speed and debugging.
