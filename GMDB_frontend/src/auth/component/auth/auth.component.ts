import { Component, ElementRef, ViewChild } from '@angular/core';
import { Router } from '@angular/router';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-auth',
  templateUrl: './auth.component.html',
  styleUrls: ['./auth.component.css'],
})
export class AuthComponent {
  @ViewChild('loginINPT')
  private loginINPT!: ElementRef;

  @ViewChild('nameINPT')
  private nameINPT!: ElementRef;

  @ViewChild('surnameINPT')
  private surnameINPT!: ElementRef;

  @ViewChild('passwordINPT')
  private passwordINPT!: ElementRef;

  @ViewChild('personalCodeINPT')
  private personalCodeINPT!: ElementRef;

  @ViewChild('mailINPT')
  private mailINPT!: ElementRef;

  @ViewChild('phoneNumberINPT')
  private phoneNumberCodeINPT!: ElementRef;

  @ViewChild('loginBTN')
  private loginBTN!: ElementRef;

  @ViewChild('signupBTN')
  private signupBTN!: ElementRef;

  @ViewChild('loginACT')
  private loginACT!: ElementRef;

  @ViewChild('signACT')
  private signACT!: ElementRef;

  click1() {
    const element = document.querySelector('.auth-container') as HTMLElement;

    if (element) {
      element.style.height = '30rem';
    }

    this.loginACT.nativeElement.classList.add('clicked');
    this.signACT.nativeElement.classList.remove('active');

    setTimeout(() => {
      this.loginACT.nativeElement.classList.add('active');
      this.loginACT.nativeElement.classList.remove('clicked');
      this.isLogin = true;
    });
  }

  click2() {
    const element = document.querySelector('.auth-container') as HTMLElement;

    if (element) {
      element.style.height = '50rem';
    }

    this.signACT.nativeElement.classList.add('clicked');
    this.loginACT.nativeElement.classList.remove('active');

    setTimeout(() => {
      this.signACT.nativeElement.classList.add('active');
      this.signACT.nativeElement.classList.remove('clicked');
      this.isLogin = false;
    }, 300);
  }

  public isLogin: boolean = true;

  formData = {
    name: '',
    email: '',
  };

  constructor(private api: ApiServiceService, private router: Router) {
    this.api.fetchData().subscribe((response) => {
      this.router.navigate(['/home']);
    });
  }

  login() {
    this.loginBTN.nativeElement.classList.add('clicked');

    setTimeout(() => {
      this.loginBTN.nativeElement.classList.remove('clicked');
    }, 300);
    const name = this.loginINPT.nativeElement.value;
    const password = this.passwordINPT.nativeElement.value;
    if (name && password) {
      this.api.loginUser(name, password).subscribe(
        (response) => {
          console.log(response);
          this.loginBTN.nativeElement.classList.add('success');
          this.router.navigate(['home', 'accounts']);

          setTimeout(() => {
            this.loginBTN.nativeElement.classList.remove('success');
          }, 500);
        },
        (error) => {
          this.loginBTN.nativeElement.classList.add('error');

          this.nameINPT.nativeElement.value = '';
          this.passwordINPT.nativeElement.value = '';
          setTimeout(() => {
            this.loginBTN.nativeElement.classList.remove('error');
          }, 500);
        }
      );
    } else {
      this.loginBTN.nativeElement.classList.add('error');

      setTimeout(() => {
        this.loginBTN.nativeElement.classList.remove('error');
      }, 500);
    }
  }

  signup() {
    this.signupBTN.nativeElement.classList.add('clicked');
    setTimeout(() => {
      this.signupBTN.nativeElement.classList.remove('clicked');
    }, 300);

    const name = this.nameINPT.nativeElement.value;
    const password = this.passwordINPT.nativeElement.value;
    const login = this.nameINPT.nativeElement.value;
    const surname = this.surnameINPT.nativeElement.value;
    const mail = this.mailINPT.nativeElement.value;
    const personalCode = this.personalCodeINPT.nativeElement.value;
    const phoneNumber = this.phoneNumberCodeINPT.nativeElement.value;

    if (
      name &&
      password &&
      login &&
      surname &&
      mail &&
      personalCode &&
      phoneNumber
    ) {
      this.api
        .createUser(
          mail,
          password,
          login,
          name,
          surname,
          personalCode,
          phoneNumber
        )
        .subscribe(
          (response) => {
            this.signupBTN.nativeElement.classList.add('success');

            setTimeout(() => {
              this.signupBTN.nativeElement.classList.remove('success');
            }, 500);
          },
          (error) => {
            this.signupBTN.nativeElement.classList.add('error');

            this.nameINPT.nativeElement.value = '';
            this.passwordINPT.nativeElement.value = '';

            setTimeout(() => {
              this.signupBTN.nativeElement.classList.remove('error');
            }, 500);
          }
        );
    } else {
      this.signupBTN.nativeElement.classList.add('error');

      setTimeout(() => {
        this.signupBTN.nativeElement.classList.remove('error');
      }, 500);
    }
  }
}
