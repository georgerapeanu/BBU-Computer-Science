function x=solve(A, b, method)
  if(strcmp(method, "qr"))
    # QR = A
    # Q' = Q^-1
    # Ax=b
    # QRx = b
    # Rx = Q'b
    [Q, R] = qr(A);
    x = backsubst(R, Q' * b);
  elseif(strcmp(method, "chol"))
    # R' * R = A
    # R' * R * x = b
    # R' is lower, R is upper 
    R = chol(A)
    x = backsubst(R, forwardsubst(R', b));
  elseif(strcmp(method, "lu"))
    [L, U, P] = lu(A);
    # P * A = LU
    # Ax = b
    # PAx = Pb
    # LUx = Pb
    x = backsubst(U, forwardsubst(L, P * b));
  else 
    x = 1 / 0
  endif
endfunction