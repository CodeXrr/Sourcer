-------------=[ S O U R C E R ]=----------------------------------------

Scans source files and builds a index of objects in source files.


PURPOSE: This project is inteded to be used as a source code analysis tool for large projects. It makes a index of all Function Definitions, Variable Declerations, Function References, and any basic information pertaining to a source-file. It abstracts each object as an entity. For example, comment_entity, function_entity, variable_entity and so on.

My goal is to expand this type of functionallity for security realated work: simulated execution, basic-coding error detection, visual-stack (memory-corruption detection)

STAGES OF PRJECT: [1] Debug/Logic: The first stage of the project is a layout of the logic, the goal for this stage is to define all the data, functions, and relating src-files needed to create a solid foundation to build upon. It primarly deals with scaning a single source file (filescan) and recognizing entities within in the file and storing them entities into a index. The output of the program prints exactly how its ran byprinting byte for byte.

    © 2022 GitHub, Inc.

    Terms
    Privacy
    Security
    Status
    Docs
    Contact GitHub
    Pricing
    API
    Training
    Blog
    About


