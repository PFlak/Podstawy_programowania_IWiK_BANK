import { Component, ElementRef, ViewChild, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent implements OnInit {
  @ViewChild('logoutBTN', { static: true })
  private logoutBTN!: ElementRef<HTMLButtonElement>;

  @ViewChild('accounts', { static: true })
  private accountsBTN!: ElementRef<HTMLButtonElement>;

  @ViewChild('atm', { static: true })
  private atmBTN!: ElementRef<HTMLButtonElement>;

  @ViewChild('transfer', { static: true })
  private transferBTN!: ElementRef<HTMLButtonElement>;

  @ViewChild('history', { static: true })
  private historyBTN!: ElementRef<HTMLButtonElement>;

  @ViewChild('admin', { static: true })
  private adminBTN!: ElementRef<HTMLButtonElement>;

  public name$: string = '';
  public role$: string = '';

  constructor(private api: ApiServiceService, private router: Router) { }

  ngOnInit(): void {
    this.api.Name$.subscribe((response) => {
      this.name$ = response;
    });

    this.api.Role$.subscribe((response) => {
      console.log(response);
      this.role$ = response;
      this.adminCheck(response);
    });
  }

  adminCheck(response: string) {
    if (response === 'ADMIN') {
      this.adminBTN.nativeElement.classList.remove('disactive');
    } else {
      this.adminBTN.nativeElement.classList.add('disactive');
    }
  }

  logout() {
    this.logoutBTN.nativeElement.classList.add('clicked');

    setTimeout(() => {
      this.logoutBTN.nativeElement.classList.remove('clicked');
    }, 300);

    this.api.logoutUser(this.name$).subscribe(
      (response) => {
        this.logoutBTN.nativeElement.classList.add('success');

        setTimeout(() => {
          this.logoutBTN.nativeElement.classList.remove('success');
        }, 500);
      },
      (error) => {
        this.logoutBTN.nativeElement.classList.add('error');

        setTimeout(() => {
          this.logoutBTN.nativeElement.classList.remove('error');
        }, 500);
      }
    );
  }

  click1() {
    this.accountsBTN.nativeElement.classList.add('clicked');
    setTimeout(() => {
      this.accountsBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click2() {
    this.atmBTN.nativeElement.classList.add('clicked');
    setTimeout(() => {
      this.atmBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click3() {
    this.transferBTN.nativeElement.classList.add('clicked');
    setTimeout(() => {
      this.transferBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click4() {
    this.historyBTN.nativeElement.classList.add('clicked');
    setTimeout(() => {
      this.historyBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click5() {
    if (this.role$ === 'ADMIN') {
      this.adminBTN.nativeElement.classList.remove('disactive');
      this.adminBTN.nativeElement.classList.add('clicked');
      setTimeout(() => {
        this.adminBTN.nativeElement.classList.remove('clicked');
      }, 300);
    } else {
      this.adminBTN.nativeElement.classList.add('disactive');
    }
  }
}
