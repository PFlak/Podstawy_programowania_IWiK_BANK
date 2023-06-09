import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HomeComponent } from './components/home/home.component';
import { HomeRoutingModule } from './home-routing.module';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule, RouterOutlet } from '@angular/router';
import { AccountsComponent } from './components/accounts/accounts.component';
import { AtmComponent } from './components/atm/atm/atm.component';
import { AdminComponent } from './components/admin/admin/admin.component';
import { HistoryComponent } from './components/history/history/history.component';
import { TransferComponent } from './components/transfer/transfer/transfer.component';

@NgModule({
  declarations: [HomeComponent, AccountsComponent, AtmComponent, AdminComponent, HistoryComponent, TransferComponent],
  imports: [CommonModule, HomeRoutingModule, HttpClientModule, RouterModule],
})
export class HomeModule {}
