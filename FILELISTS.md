# 파일 리스트

- core - 코어 파일
  - arch
    - Archituecture
    - ArchitectureRepository
    - Capstone
    - CapstoneInstruction
    - Disassembler
    - Instruction
    - Instructions
    - Register
    - Registers
    - RegistersConstructor
  - image
    - ByteSource
    - Image
    - Platform
    - reader
    - Relocation
    - Section
    - Symbol
  - input
    - ParseError
    - Parser
    - ParseRepository
    - Utils
  - ir
    - calling
    - cflow
    - cgen
    - dflow
    - liveness
    - misc
    - types
    - vars
    - BasicBlock
    - CFG
    - Dominators
    - Function
    - Functions
    - FunctionGenerator
    - Jump
    - JumpTarget
    - MemoryDomain
    - MemoryLocation
    - Program
    - Statement
    - Statements
    - Term
    - Terms
  - irgen
    - Expressions
    - InstructionAnalyzer
    - InvalidInstructionException
    - IRGenerator
  - likec
    - ArgumentDeclartion
    - BinaryOperator
    - Block
    - Break
    - CallOperator
    - CaseLabel
    - Commentable
    - CompilationUnit
    - Continue
    - Declaration
    - DefaultLabel
    - DoWhile
    - Expression
    - ExpressionStatement
    - FunctionDeclaration
    - FunctionDefinition
    - FunctionIdentifier
    - FunctionPointerType
    - Goto
    - If
    - InlineAssembly
    - IntegerConstant
    - LabelDeclaration
    - LabelIdentifier
    - LabelStatement
    - MemberAccessOperator
    - MemberDeclaration
    - Return
    - Simplifier
    - Statement
    - String
    - StructType
    - StructTypeDeclaration
    - Switch
    - Tree
    - TreeNode
    - TreePrinter
    - Type
    - TypeCalculator
    - Typecast
    - Types
    - UnaryOperator
    - UndeclaredIdentifier
    - Utils
    - VariableDeclaration
    - VariableIdentifiers
    - While
  - mangling - export된 함수 이름을 복구하는 기능
    - DefaultDemangler
    - Demangler
  - Context - 디컴파일러 내부 정보가 담겨져있는 파일 (클래스 선언문)
  - Driver - 디컴파일러에서 공통적으로 사용되는 부분을 통합되어 사용될 수 있도록 관리하는 파일
  디스어셈블이나 파싱등은 아키텍쳐에 따라, 파일 타입에 따라 달라지는데 해당 파일을 통해, 각각의 경우에 맞는 함수를 호출하는것으로 보인다.
    1. 파싱
    2. 디스어셈블(기본:코드)
    3. 디스어셈블(섹션)
    4. 디스어셈블(시작 ~ 끝 바이트)
    5. 디컴파일
  - MasterAnalyzer - 디컴파일러가 수행하는 명령들을 정의하는 파일
  전체 디컴파일 과정은 다음과 같은 순으로 이루어진다.
    1. 프로그램 생성
    2. 함수 생성
    3. 후크 생성
    4. call문 변환
    5. 데이터 흐름 분석
    6. 실행 흐름 분석
    7. 시그니처 재작성
    8. 데이터 흐름 분석 2
    9. 변수 재작성
    10. 구조체 분석
    11. 실행 흐름 분석 2
    12. 타입 재작성
    13. 트리 작성
- common - 공통 파일
  - BitTwiddling
  - Branding
  - ByteOrder
  - CancellationToken
  - CheckedCast
  - DisjointSet
  - Escaping
  - Exception
  - Foreach
  - ilist
  - Logger
  - LogLevel
  - LogToken
  - make_unique
  - Printable
  - PrintCallback
  - Range
  - RangeClass
  - SignalLogger
  - SizedValue
  - StreamLogger
  - StringToInt
  - Subclass
  - Types
  - Unreachable
  - Unused
  - Version
- arch - 아키텍처 별 달라지는 기능들에 대해 정의되어있는 파일
  - arm
  - x86
- input - 여러 입력 포맷 별 달라지는 기능에 대해 정의되어있는 파일
  - PE
  - MACH-O
  - LE
  - ELF
