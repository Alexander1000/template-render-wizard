# syntax tree
# t - token
# s - syntax rule

s:injectValue [t:openTagValue t:plainValue t:closeTagValue]
s:expr [t:exprValue]
s:expr [t:roundBracketOpen s:expr t:roundBracketClose]
s:expr [s:expr t:mathOp(*|/) s:expr]
s:expr [s:expr t:mathOp(+|-) s:expr]
s:if_control [t:openControlTag t:keyword(if) s:expr t:closeControlTag]
s:else_control [t:openControlTag t:keyword(else) t:closeControlTag]
s:endif_control [t:openControlTag t:keyword(endif) t:closeControlTag]
s:for_control [t:openControlTag t:keyword(for) t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
s:for_control [t:openControlTag t:keyword(for) t:plainValue t:dot t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
s:endfor_control [t:openControlTag t:keyword(endfor) t:closeControlTag]
s:if_stmt [s:if_control s:body s:endif_control]
s:if_stmt [s:if_control s:body s:else_control s:body s:endif_control]
s:for_stmt [s:for_control s:body s:endfor_control]
s:body [t:plainText]
s:body [s:injectValue]
s:body [s:if_stmt]
s:body [s:for_stmt]
s:body [s:body s:body]
