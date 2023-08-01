import { TestBed } from '@angular/core/testing';

import { UnauthorizedRedirectionInterceptor } from './unauthorized-redirection.interceptor';

describe('UnauthorizedRedirectionInterceptor', () => {
  beforeEach(() => TestBed.configureTestingModule({
    providers: [
      UnauthorizedRedirectionInterceptor
      ]
  }));

  it('should be created', () => {
    const interceptor: UnauthorizedRedirectionInterceptor = TestBed.inject(UnauthorizedRedirectionInterceptor);
    expect(interceptor).toBeTruthy();
  });
});
