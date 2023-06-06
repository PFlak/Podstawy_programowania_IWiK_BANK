import { Component, ElementRef, ViewChild } from '@angular/core';
import { Router } from '@angular/router';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-auth',
  templateUrl: './auth.component.html',
  styleUrls: ['./auth.component.css'],
})
export class AuthComponent {
  @ViewChild('nameINPT')
  private nameINPT!: ElementRef;

  @ViewChild('passwordINPT')
  private passwordINPT!: ElementRef;

  @ViewChild('loginBTN')
  private loginBTN!: ElementRef;

  @ViewChild('signupBTN')
  private signupBTN!: ElementRef;

  public isSignClicked: boolean = false;
  public isLoginClicked: boolean = false;

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
    const name = this.nameINPT.nativeElement.value;
    const password = this.passwordINPT.nativeElement.value;
    if (name && password) {
      this.api.loginUser(name, password).subscribe(
        (response) => {
          console.log(response);
          this.loginBTN.nativeElement.classList.add('success');

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

    if (name && password) {
      this.api.createUser(name, password).subscribe(
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
