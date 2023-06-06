import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AuthComponent } from 'src/auth/component/auth/auth.component';
import { HomeComponent } from 'src/home/components/home/home.component';

const routes: Routes = [
  {
    path: '',
    component: AuthComponent,
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
  },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
