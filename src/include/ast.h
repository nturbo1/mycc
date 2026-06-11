#ifndef SRC_INCLUDE_AST_H
#define SRC_INCLUDE_AST_H

#include "token.h"
#include "darray.h"

typedef struct AstNode
{
    const size_t line;
    const size_t col;
}
AstNode;

typedef struct AstFile
{
    // DArray<Decl*>
    DArray* decls;  // A list of declarations in a src file
}
AstFile;

AstFile* new_astfile(DArray* decls);

typedef enum {
    CONST_TYPE_QUALIFIER,
    RESTRICT_TYPE_QUALIFIER,
    VOLATILE_TYPE_QUALIFIER,

    NO_TYPE_QUALIFIER,
} TypeQualifier;

typedef enum {
    TYPEDEF_STORAGE_SPECIFIER,
    EXTERN_STORAGE_SPECIFIER,
    STATIC_STORAGE_SPECIFIER,
    AUTO_STORAGE_SPECIFIER,
    REGISTER_STORAGE_SPECIFIER,

    NO_STORAGE_SPECIFIER,
} StorageClassSpecifier;

typedef enum {
    VOID_TYPE_SPECIFIER,
    CHAR_TYPE_SPECIFIER,
    SHORT_TYPE_SPECIFIER,
    INT_TYPE_SPECIFIER,
    LONG_TYPE_SPECIFIER,
    FLOAT_TYPE_SPECIFIER,
    DOUBLE_TYPE_SPECIFIER,
    SIGNED_TYPE_SPECIFIER,
    UNSIGNED_TYPE_SPECIFIER,
    _BOOL_TYPE_SPECIFIER,
    _COMPLEX_TYPE_SPECIFIER,
    STRUCT_TYPE_SPECIFIER,
    UNION_TYPE_SPECIFIER,
    ENUM_TYPE_SPECIFIER,
    TYPEDEF_NAME_TYPE_SPECIFIER,

    NO_TYPE_SPECIFIER,
} TypeSpecifier;

typedef enum {
    INLINE_FUNC_SPECIFIER,

    NO_FUNC_SPECIFIER,
} FuncSpecifier;

typedef struct
{
    StorageClassSpecifier strg_class;
    TypeQualifier type_qualfr;
    TypeSpecifier type;
    FuncSpecifier func_specfr;
}
DeclSpecifier;

// ==============================================================================
// Expresssions and types
// ==============================================================================
typedef struct {
    const AstNode node;
} Expr;

typedef struct {
    const Expr expr;
    const char* name;
} Ident;

// Type represents a data type:
//  - Built-in types such as char, short, int, long, float, double, etc.
//  - Custom, composite types such as struct, enum, union, etc.
typedef struct {
    const TypeSpecifier spec;
    const Ident* ident;
    // TODO: Add `fields` field to have a list of fields for composite types such as struct!
} Type;

// A Field represents a Field declaration list in a struct type, or a parameter/result declaration
// in a signature.
typedef struct {
    const Ident* ident;   // field/parameter name
    const Type* type;     // field/parameter type
} Field;

typedef struct {
    const TokenType op; // the unary operator
    const Expr epxr;
} UnaryExpr;

// ==============================================================================
// Statements
// ==============================================================================

typedef struct {
    const AstNode node;
} Stmt;

typedef struct {
    Stmt stmt_base;

    // DArray<Stmt>
    DArray* stmts;
} BlockStmt;

// ==============================================================================
// Declarations
// ==============================================================================
typedef enum {
    FUNC_DECL_TYPE,
} DeclType;

// Represents a declaration. The parent struct type of all declaration
// struct types.
typedef struct {
    const AstNode node;
    const Ident* ident;
    const DeclType decl_type;
} Decl;

typedef struct {
    const Decl decl;
    const FuncSpecifier spec;
    const StorageClassSpecifier stor_spec;
    const Type* ret_type;

    // DArray<Field>
    const DArray* parameters;
    const BlockStmt* body;
} FuncDecl;

#endif // SRC_INCLUDE_AST_H
