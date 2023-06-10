import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AuthComponent } from 'src/auth/component/auth/auth.component';
import { AccountsComponent } from 'src/home/components/accounts/accounts.component';
import { AdminComponent } from 'src/home/components/admin/admin/admin.component';
import { AtmComponent } from 'src/home/components/atm/atm/atm.component';
import { HistoryComponent } from 'src/home/components/history/history/history.component';
import { HomeComponent } from 'src/home/components/home/home.component';
import { TransferComponent } from 'src/home/components/transfer/transfer/transfer.component';

const routes: Routes = [
  {
    path: '',
    component: HomeComponent,
    data: { title: 'GMDBP' },
  },
  {
    path: 'auth',
    component: AuthComponent,
    data: { title: 'GMDBP | Authorization' },
  },
  {
    path: 'home',
    component: HomeComponent,
    data: { title: 'GMDBP | HOME' },
    children: [
      {
        path: 'accounts',
        component: AccountsComponent,
      },
      {
        path: 'atm',
        component: AtmComponent,
      },
      {
        path: 'transfer',
        component: TransferComponent,
      },
      {
        path: 'history',
        component: HistoryComponent,
      },
      {
        path: 'admin',
        component: AdminComponent,
      },
    ],
  },
  {
    path: 'accounts',
    component: AccountsComponent,
    data: { title: 'GMDBP | accounts' },
  },
  {
    path: 'atm',
    component: AtmComponent,
    data: { title: 'GMDBP | atm' },
  },
  {
    path: 'transfer',
    component: TransferComponent,
    data: { title: 'GMDBP | transfer' },
  },
  {
    path: 'admin',
    component: AdminComponent,
    data: { title: 'GMDBP | admin' },
  },
  {
    path: 'history',
    component: HistoryComponent,
    data: { title: 'GMDBP | history' },
  },
];



@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule { }
