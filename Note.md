# Snowman Decompiler

## 디컴파일 진행 과정

nc/core/MasterAnalyzer.cpp -> MasterAnalyzer::decompile

1. Create Program
2. Create Functions
3. Create Hooks
4. Detect Calling Conventions
5. Dataflow Analysis
6. Liveness Analysis
7. Reconstruct Signatures
8. Dataflow Analysis
9. Reconstruct Variables
10. Structural Analysis
11. Liveness Analysis
12. Reconstruct Types
13. Generate tree
