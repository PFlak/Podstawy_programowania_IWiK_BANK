import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HomeComponent } from './components/home/home.component';
import { HomeRoutingModule } from './home-routing.module';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule, RouterOutlet } from '@angular/router';
import { AccountsComponent } from './components/accounts/accounts.component';

@NgModule({
  declarations: [HomeComponent, AccountsComponent],
  imports: [CommonModule, HomeRoutingModule, HttpClientModule, RouterModule],
})
export class HomeModule {}
