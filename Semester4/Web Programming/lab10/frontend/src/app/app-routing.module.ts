import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LogsOverviewComponent } from './assets/logs-overview/logs-overview.component';
import { LogCreateComponent } from './assets/log-create/log-create.component';
import { LogDetailsComponent } from './assets/log-details/log-details.component';
import { LogEditComponent } from './assets/log-edit/log-edit.component';
import { LogDeleteComponent } from './assets/log-delete/log-delete.component';

const routes: Routes = [
  {
    path: '',
    redirectTo: '/logs',
    pathMatch: 'full'
  },
  {
    path: 'logs',
    component: LogsOverviewComponent
  },
  {
    path: 'logs/create',
    component: LogCreateComponent
  },
  {
    path: 'logs/:id',
    component: LogDetailsComponent
  },
  {
    path: 'logs/:id/edit',
    component: LogEditComponent
  },
  {
    path: 'logs/:id/delete',
    component: LogDeleteComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
