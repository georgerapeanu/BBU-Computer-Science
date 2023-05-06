import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LogEditComponent } from './log-edit.component';

describe('LogEditComponent', () => {
  let component: LogEditComponent;
  let fixture: ComponentFixture<LogEditComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ LogEditComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(LogEditComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
