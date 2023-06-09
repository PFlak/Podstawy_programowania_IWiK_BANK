import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AtmComponent } from './atm.component';

describe('AtmComponent', () => {
  let component: AtmComponent;
  let fixture: ComponentFixture<AtmComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AtmComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(AtmComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
