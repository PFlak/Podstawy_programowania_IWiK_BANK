import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AuthComponent } from './component/auth/auth.component';
import { AuthRoutingModule } from './auth-routing.module';
import { HttpClientModule } from '@angular/common/http';

@NgModule({
  declarations: [AuthComponent],
  imports: [CommonModule, AuthRoutingModule, HttpClientModule],
})
export class AuthModule {}
