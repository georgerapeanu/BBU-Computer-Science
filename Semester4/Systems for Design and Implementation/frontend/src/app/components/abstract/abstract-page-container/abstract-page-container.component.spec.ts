import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AbstractPageContainerComponent } from './abstract-page-container.component';

describe('AbstractPageContainerComponent', () => {
  let component: AbstractPageContainerComponent;
  let fixture: ComponentFixture<AbstractPageContainerComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AbstractPageContainerComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(AbstractPageContainerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
