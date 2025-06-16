# Roadmap :

### Preparations :

- [ ] Voir les bases de Git :
    - https://learngitbranching.js.org//
- [ ] Voir la Doc de bash :
    - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
        - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Syntax
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Operation
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Quoting
                - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Single-Quotes
                - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Double-Quotes
        - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Commands
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Simple-Commands
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Pipelines
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Lists
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Compound-Commands
                - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Command-Grouping
        - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Expansions
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Parameter-Expansion
                - Uniquement pour '$VAR' pour les variables d'environnements, ainsi que '$?'.
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Filename-Expansion
            - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Quote-Removal
        - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Redirections
        - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Executing-Commands

### Parsing :

- [ ] Tokenizer
    - [ ] Re-regarder la premiere partie de la peer-review pour tout voler
- [ ] AST
    - [ ] Aled je comprend pas comment ca marche
    - [ ] Qu'est ce que c'est meme ?????

### Exec :

- [ ] Gestion des signaux :
    - [ ] Utiliser sigaction dans le parent pour ignorer le signal de CTRL+\, puis dans les enfants pour revenir au comportement par defaut
        - (merci mgalvez pour le tuto)
    - [ ] Gerer les signaux de sorties comme dans le pipex du bogoss de la team
- [ ] Expand
    - [ ] C'est quoi cette merde frr
- [ ] Forks&Pipes
    - [ ] Certainement juste un copier/coller de pipex
