# syntax tree
# t - token
# s - syntax rule
# build: syntax-tree -s syntax.s -i src/trw/syntax/tree.cpp

injectValue [t:openTagValue t:plainValue t:closeTagValue]
expr [t:exprValue]
expr [t:roundBracketOpen s:expr t:roundBracketClose]
expr [s:expr t:mathOpHigh s:expr]
expr [s:expr t:mathOp s:expr]
cmpBool [t:keyword(and)]
cmpBool [t:keyword(or)]
cmpExpr [s:expr t:compare s:expr]
boolExpr [s:expr s:cmpBool s:expr]
boolExpr [s:cmpExpr s:cmpBool s:cmpExpr]
boolExpr [s:expr s:cmpBool s:cmpExpr]
boolExpr [s:cmpExpr s:cmpBool s:expr]
expr_control [t:openControlTag s:expr t:closeControlTag]
expr_control [t:openControlTag s:cmpExpr t:closeControlTag]
expr_control [t:openControlTag s:boolExpr t:closeControlTag]
if_control [t:openControlTag t:keyword(if) s:expr t:closeControlTag]
if_control [t:openControlTag t:keyword(if) s:cmpExpr t:closeControlTag]
if_control [t:openControlTag t:keyword(if) s:boolExpr t:closeControlTag]
else_control [t:openControlTag t:keyword(else) t:closeControlTag]
endif_control [t:openControlTag t:keyword(endif) t:closeControlTag]
for_control [t:openControlTag t:keyword(for) t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
for_control [t:openControlTag t:keyword(for) t:plainValue t:comma t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
endfor_control [t:openControlTag t:keyword(endfor) t:closeControlTag]
if_stmt [s:if_control s:body s:endif_control]
if_stmt [s:if_control s:body s:else_control s:body s:endif_control]
for_stmt [s:for_control s:body s:endfor_control]
include_with_value_stmt [s:expr]
include_with_value_stmt [s:cmpExpr]
include_with_value_stmt [s:boolExpr]
include_with_pair [t:includeWithKey t:doubleDot s:include_with_value_stmt]
include_with_stmt [s:include_with_pair t:comma s:include_with_pair]
include_with_stmt [s:include_with_pair]
include_with_stmt [s:include_with_stmt t:comma s:include_with_stmt]
include_stmt [t:openControlTag t:keyword(include) t:filePath t:closeControlTag]
include_stmt [t:openControlTag t:keyword(include) t:filePath t:keyword(with) t:openBrace s:include_with_stmt t:closeBrace t:closeControlTag]
body [t:plainText]
body [s:injectValue]
body [s:expr_control]
body [s:if_stmt]
body [s:for_stmt]
body [s:include_stmt]
body [s:body s:body]
